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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * _wfopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  wide_string (char const*,struct gc_arena*) ; 

FILE *
platform_fopen(const char *path, const char *mode)
{
#ifdef _WIN32
    struct gc_arena gc = gc_new();
    FILE *f = _wfopen(wide_string(path, &gc), wide_string(mode, &gc));
    gc_free(&gc);
    return f;
#else
    return fopen(path, mode);
#endif
}