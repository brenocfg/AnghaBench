#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsstr_t ;
struct TYPE_4__ {int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
typedef  TYPE_1__ jsstr_rope_t ;
struct TYPE_5__ {int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
#define  JSSTR_HEAP 130 
#define  JSSTR_INLINE 129 
#define  JSSTR_ROPE 128 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 TYPE_3__* jsstr_as_heap (int /*<<< orphan*/ *) ; 
 TYPE_1__* jsstr_as_rope (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ ) ; 
 int jsstr_tag (int /*<<< orphan*/ *) ; 

void jsstr_free(jsstr_t *str)
{
    switch(jsstr_tag(str)) {
    case JSSTR_HEAP:
        heap_free(jsstr_as_heap(str)->buf);
        break;
    case JSSTR_ROPE: {
        jsstr_rope_t *rope = jsstr_as_rope(str);
        jsstr_release(rope->left);
        jsstr_release(rope->right);
        break;
    }
    case JSSTR_INLINE:
        break;
    }

    heap_free(str);
}