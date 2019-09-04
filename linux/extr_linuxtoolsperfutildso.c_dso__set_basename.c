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
struct dso {int /*<<< orphan*/  long_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  basename (char*) ; 
 int /*<<< orphan*/  dso__set_short_name (struct dso*,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dso__set_basename(struct dso *dso)
{
       /*
        * basename() may modify path buffer, so we must pass
        * a copy.
        */
       char *base, *lname = strdup(dso->long_name);

       if (!lname)
               return;

       /*
        * basename() may return a pointer to internal
        * storage which is reused in subsequent calls
        * so copy the result.
        */
       base = strdup(basename(lname));

       free(lname);

       if (!base)
               return;

       dso__set_short_name(dso, base, true);
}