#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pos; int allocated; char* s; } ;
typedef  TYPE_1__ _tmp_string_t ;

/* Variables and functions */
 int INIT_SIZE ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_MemoryError ; 
 char* realloc (char*,size_t) ; 

__attribute__((used)) static int
_append_char(_tmp_string_t *s, char c)
{
    if (s->pos >= s->allocated) {
        char *p;
        size_t to_alloc = (s->allocated == 0) ? INIT_SIZE : (2 * s->allocated);

        p = realloc(s->s, to_alloc);
        if (p == NULL) {
            PyErr_SetString(PyExc_MemoryError, "memory allocation failed");
            return -1;
        }
        s->s = p;
        s->allocated = to_alloc;
    }
    s->s[s->pos] = c;
    ++s->pos;
    return 0;
}