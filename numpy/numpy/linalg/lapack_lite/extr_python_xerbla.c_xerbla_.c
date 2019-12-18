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
typedef  int /*<<< orphan*/  integer ;
typedef  int /*<<< orphan*/  format ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  PyGILState_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  PyGILState_Ensure () ; 
 int /*<<< orphan*/  PyGILState_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyOS_snprintf (char*,int,char const*,int,char*,int /*<<< orphan*/ ) ; 

int xerbla_(char *srname, integer *info)
{
        static const char format[] = "On entry to %.*s" \
                " parameter number %d had an illegal value";
        char buf[sizeof(format) + 6 + 4];   /* 6 for name, 4 for param. num. */

        int len = 0; /* length of subroutine name*/
#ifdef WITH_THREAD
        PyGILState_STATE save;
#endif

        while( len<6 && srname[len]!='\0' )
                len++;
        while( len && srname[len-1]==' ' )
                len--;
#ifdef WITH_THREAD
        save = PyGILState_Ensure();
#endif
        PyOS_snprintf(buf, sizeof(buf), format, len, srname, *info);
        PyErr_SetString(PyExc_ValueError, buf);
#ifdef WITH_THREAD
        PyGILState_Release(save);
#endif

        return 0;
}