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
struct gc_arena {int dummy; } ;

/* Variables and functions */
 int _wchdir (int /*<<< orphan*/ ) ; 
 int chdir (char const*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  wide_string (char const*,struct gc_arena*) ; 

int
platform_chdir(const char *dir)
{
#ifdef HAVE_CHDIR
#ifdef _WIN32
    int res;
    struct gc_arena gc = gc_new();
    res = _wchdir(wide_string(dir, &gc));
    gc_free(&gc);
    return res;
#else  /* ifdef _WIN32 */
    return chdir(dir);
#endif
#else  /* ifdef HAVE_CHDIR */
    return -1;
#endif
}