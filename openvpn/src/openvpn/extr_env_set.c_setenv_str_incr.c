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
struct env_set {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D_TLS_DEBUG_MED ; 
 int /*<<< orphan*/ * env_set_get (struct env_set*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* gc_malloc (size_t const,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  openvpn_snprintf (char*,size_t const,char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  setenv_str (struct env_set*,char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

void
setenv_str_incr(struct env_set *es, const char *name, const char *value)
{
    unsigned int counter = 1;
    const size_t tmpname_len = strlen(name) + 5; /* 3 digits counter max */
    char *tmpname = gc_malloc(tmpname_len, true, NULL);
    strcpy(tmpname, name);
    while (NULL != env_set_get(es, tmpname) && counter < 1000)
    {
        ASSERT(openvpn_snprintf(tmpname, tmpname_len, "%s_%u", name, counter));
        counter++;
    }
    if (counter < 1000)
    {
        setenv_str(es, tmpname, value);
    }
    else
    {
        msg(D_TLS_DEBUG_MED, "Too many same-name env variables, ignoring: %s", name);
    }
    free(tmpname);
}