#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sigaction {int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
struct OPENSSL_s390xcap_st {int* stfle; int /*<<< orphan*/ * kdsa; int /*<<< orphan*/ * pcc; int /*<<< orphan*/ * kma; int /*<<< orphan*/ * prno; int /*<<< orphan*/ * kmf; int /*<<< orphan*/ * kmo; int /*<<< orphan*/ * kmctr; int /*<<< orphan*/ * kmac; int /*<<< orphan*/ * kmc; int /*<<< orphan*/ * km; int /*<<< orphan*/ * klmd; int /*<<< orphan*/ * kimd; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  ill_act ;
struct TYPE_2__ {int* stfle; int /*<<< orphan*/ * kdsa; int /*<<< orphan*/ * pcc; int /*<<< orphan*/ * kma; int /*<<< orphan*/ * prno; int /*<<< orphan*/ * kmf; int /*<<< orphan*/ * kmo; int /*<<< orphan*/ * kmctr; int /*<<< orphan*/ * kmac; int /*<<< orphan*/ * kmc; int /*<<< orphan*/ * km; int /*<<< orphan*/ * klmd; int /*<<< orphan*/ * kimd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_HWCAP ; 
 unsigned long const HWCAP_S390_STFLE ; 
 unsigned long const HWCAP_S390_VX ; 
 int /*<<< orphan*/  OPENSSL_s390x_facilities () ; 
 int /*<<< orphan*/  OPENSSL_s390x_functions () ; 
 TYPE_1__ OPENSSL_s390xcap_P ; 
 int /*<<< orphan*/  OPENSSL_vx_probe () ; 
 int S390X_CAPBIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S390X_VX ; 
 int /*<<< orphan*/  S390X_VXD ; 
 int /*<<< orphan*/  S390X_VXE ; 
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/ * env ; 
 unsigned long getauxval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int /*<<< orphan*/  ill_handler ; 
 int /*<<< orphan*/  ill_jmp ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_env (struct OPENSSL_s390xcap_st*) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  sigdelset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sigsetjmp (int /*<<< orphan*/ ,int) ; 

void OPENSSL_cpuid_setup(void)
{
    struct OPENSSL_s390xcap_st cap;

    if (OPENSSL_s390xcap_P.stfle[0])
        return;

    /* set a bit that will not be tested later */
    OPENSSL_s390xcap_P.stfle[0] |= S390X_CAPBIT(0);

#if defined(OSSL_IMPLEMENT_GETAUXVAL)
    {
        const unsigned long hwcap = getauxval(AT_HWCAP);

        /* protection against missing store-facility-list-extended */
        if (hwcap & HWCAP_S390_STFLE)
            OPENSSL_s390x_facilities();

        /* protection against disabled vector facility */
        if (!(hwcap & HWCAP_S390_VX)) {
            OPENSSL_s390xcap_P.stfle[2] &= ~(S390X_CAPBIT(S390X_VX)
                                             | S390X_CAPBIT(S390X_VXD)
                                             | S390X_CAPBIT(S390X_VXE));
        }
    }
#else
    {
        sigset_t oset;
        struct sigaction ill_act, oact_ill, oact_fpe;

        memset(&ill_act, 0, sizeof(ill_act));
        ill_act.sa_handler = ill_handler;
        sigfillset(&ill_act.sa_mask);
        sigdelset(&ill_act.sa_mask, SIGILL);
        sigdelset(&ill_act.sa_mask, SIGFPE);
        sigdelset(&ill_act.sa_mask, SIGTRAP);

        sigprocmask(SIG_SETMASK, &ill_act.sa_mask, &oset);
        sigaction(SIGILL, &ill_act, &oact_ill);
        sigaction(SIGFPE, &ill_act, &oact_fpe);

        /* protection against missing store-facility-list-extended */
        if (sigsetjmp(ill_jmp, 1) == 0)
            OPENSSL_s390x_facilities();

        /* protection against disabled vector facility */
        if ((OPENSSL_s390xcap_P.stfle[2] & S390X_CAPBIT(S390X_VX))
            && (sigsetjmp(ill_jmp, 1) == 0)) {
            OPENSSL_vx_probe();
        } else {
            OPENSSL_s390xcap_P.stfle[2] &= ~(S390X_CAPBIT(S390X_VX)
                                             | S390X_CAPBIT(S390X_VXD)
                                             | S390X_CAPBIT(S390X_VXE));
        }

        sigaction(SIGFPE, &oact_fpe, NULL);
        sigaction(SIGILL, &oact_ill, NULL);
        sigprocmask(SIG_SETMASK, &oset, NULL);
    }
#endif

    env = getenv("OPENSSL_s390xcap");
    if (env != NULL) {
        if (!parse_env(&cap))
            env = NULL;
    }

    if (env != NULL) {
        OPENSSL_s390xcap_P.stfle[0] &= cap.stfle[0];
        OPENSSL_s390xcap_P.stfle[1] &= cap.stfle[1];
        OPENSSL_s390xcap_P.stfle[2] &= cap.stfle[2];
    }

    OPENSSL_s390x_functions(); /* check OPENSSL_s390xcap_P.stfle */

    if (env != NULL) {
        OPENSSL_s390xcap_P.kimd[0] &= cap.kimd[0];
        OPENSSL_s390xcap_P.kimd[1] &= cap.kimd[1];
        OPENSSL_s390xcap_P.klmd[0] &= cap.klmd[0];
        OPENSSL_s390xcap_P.klmd[1] &= cap.klmd[1];
        OPENSSL_s390xcap_P.km[0] &= cap.km[0];
        OPENSSL_s390xcap_P.km[1] &= cap.km[1];
        OPENSSL_s390xcap_P.kmc[0] &= cap.kmc[0];
        OPENSSL_s390xcap_P.kmc[1] &= cap.kmc[1];
        OPENSSL_s390xcap_P.kmac[0] &= cap.kmac[0];
        OPENSSL_s390xcap_P.kmac[1] &= cap.kmac[1];
        OPENSSL_s390xcap_P.kmctr[0] &= cap.kmctr[0];
        OPENSSL_s390xcap_P.kmctr[1] &= cap.kmctr[1];
        OPENSSL_s390xcap_P.kmo[0] &= cap.kmo[0];
        OPENSSL_s390xcap_P.kmo[1] &= cap.kmo[1];
        OPENSSL_s390xcap_P.kmf[0] &= cap.kmf[0];
        OPENSSL_s390xcap_P.kmf[1] &= cap.kmf[1];
        OPENSSL_s390xcap_P.prno[0] &= cap.prno[0];
        OPENSSL_s390xcap_P.prno[1] &= cap.prno[1];
        OPENSSL_s390xcap_P.kma[0] &= cap.kma[0];
        OPENSSL_s390xcap_P.kma[1] &= cap.kma[1];
        OPENSSL_s390xcap_P.pcc[0] &= cap.pcc[0];
        OPENSSL_s390xcap_P.pcc[1] &= cap.pcc[1];
        OPENSSL_s390xcap_P.kdsa[0] &= cap.kdsa[0];
        OPENSSL_s390xcap_P.kdsa[1] &= cap.kdsa[1];
    }
}