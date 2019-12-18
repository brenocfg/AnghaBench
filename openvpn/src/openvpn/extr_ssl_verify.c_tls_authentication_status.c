#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tls_multi {scalar_t__ tas_last; struct key_state** key_scan; } ;
struct key_state {int authenticated; int auth_deferred; scalar_t__ auth_deferred_expire; } ;

/* Variables and functions */
#define  ACF_DISABLED 131 
#define  ACF_FAILED 130 
#define  ACF_SUCCEEDED 129 
#define  ACF_UNDEFINED 128 
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DECRYPT_KEY_ENABLED (struct tls_multi*,struct key_state*) ; 
 int /*<<< orphan*/  D_TLS_ERRORS ; 
 int KEY_SCAN_SIZE ; 
 int TLS_AUTHENTICATION_DEFERRED ; 
 int TLS_AUTHENTICATION_FAILED ; 
 int TLS_AUTHENTICATION_SUCCEEDED ; 
 int TLS_AUTHENTICATION_UNDEFINED ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 unsigned int key_state_test_auth_control_file (struct key_state*) ; 
 unsigned int man_def_auth_test (struct key_state*) ; 
 scalar_t__ now ; 

int
tls_authentication_status(struct tls_multi *multi, const int latency)
{
    bool deferred = false;
    bool success = false;
    bool active = false;

#ifdef ENABLE_DEF_AUTH
    static const unsigned char acf_merge[] =
    {
        ACF_UNDEFINED, /* s1=ACF_UNDEFINED s2=ACF_UNDEFINED */
        ACF_UNDEFINED, /* s1=ACF_UNDEFINED s2=ACF_SUCCEEDED */
        ACF_UNDEFINED, /* s1=ACF_UNDEFINED s2=ACF_DISABLED */
        ACF_FAILED,  /* s1=ACF_UNDEFINED s2=ACF_FAILED */
        ACF_UNDEFINED, /* s1=ACF_SUCCEEDED s2=ACF_UNDEFINED */
        ACF_SUCCEEDED, /* s1=ACF_SUCCEEDED s2=ACF_SUCCEEDED */
        ACF_SUCCEEDED, /* s1=ACF_SUCCEEDED s2=ACF_DISABLED */
        ACF_FAILED,  /* s1=ACF_SUCCEEDED s2=ACF_FAILED */
        ACF_UNDEFINED, /* s1=ACF_DISABLED  s2=ACF_UNDEFINED */
        ACF_SUCCEEDED, /* s1=ACF_DISABLED  s2=ACF_SUCCEEDED */
        ACF_DISABLED, /* s1=ACF_DISABLED  s2=ACF_DISABLED */
        ACF_FAILED,  /* s1=ACF_DISABLED  s2=ACF_FAILED */
        ACF_FAILED,  /* s1=ACF_FAILED    s2=ACF_UNDEFINED */
        ACF_FAILED,  /* s1=ACF_FAILED    s2=ACF_SUCCEEDED */
        ACF_FAILED,  /* s1=ACF_FAILED    s2=ACF_DISABLED */
        ACF_FAILED   /* s1=ACF_FAILED    s2=ACF_FAILED */
    };
#endif /* ENABLE_DEF_AUTH */

    if (multi)
    {
        int i;

#ifdef ENABLE_DEF_AUTH
        if (latency && multi->tas_last && multi->tas_last + latency >= now)
        {
            return TLS_AUTHENTICATION_UNDEFINED;
        }
        multi->tas_last = now;
#endif /* ENABLE_DEF_AUTH */

        for (i = 0; i < KEY_SCAN_SIZE; ++i)
        {
            struct key_state *ks = multi->key_scan[i];
            if (DECRYPT_KEY_ENABLED(multi, ks))
            {
                active = true;
                if (ks->authenticated)
                {
#ifdef ENABLE_DEF_AUTH
                    unsigned int s1 = ACF_DISABLED;
                    unsigned int s2 = ACF_DISABLED;
#ifdef PLUGIN_DEF_AUTH
                    s1 = key_state_test_auth_control_file(ks);
#endif /* PLUGIN_DEF_AUTH */
#ifdef MANAGEMENT_DEF_AUTH
                    s2 = man_def_auth_test(ks);
#endif /* MANAGEMENT_DEF_AUTH */
                    ASSERT(s1 < 4 && s2 < 4);
                    switch (acf_merge[(s1<<2) + s2])
                    {
                        case ACF_SUCCEEDED:
                        case ACF_DISABLED:
                            success = true;
                            ks->auth_deferred = false;
                            break;

                        case ACF_UNDEFINED:
                            if (now < ks->auth_deferred_expire)
                            {
                                deferred = true;
                            }
                            break;

                        case ACF_FAILED:
                            ks->authenticated = false;
                            break;

                        default:
                            ASSERT(0);
                    }
#else /* !ENABLE_DEF_AUTH */
                    success = true;
#endif /* ENABLE_DEF_AUTH */
                }
            }
        }
    }

#if 0
    dmsg(D_TLS_ERRORS, "TAS: a=%d s=%d d=%d", active, success, deferred);
#endif

    if (success)
    {
        return TLS_AUTHENTICATION_SUCCEEDED;
    }
    else if (!active || deferred)
    {
        return TLS_AUTHENTICATION_DEFERRED;
    }
    else
    {
        return TLS_AUTHENTICATION_FAILED;
    }
}