#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsstr_t ;
struct TYPE_5__ {int /*<<< orphan*/ * left; int /*<<< orphan*/ * right; } ;
typedef  TYPE_1__ jsstr_rope_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {int /*<<< orphan*/  buf; } ;
struct TYPE_6__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 TYPE_4__* jsstr_as_heap (int /*<<< orphan*/ *) ; 
 TYPE_3__* jsstr_as_inline (int /*<<< orphan*/ *) ; 
 TYPE_1__* jsstr_as_rope (int /*<<< orphan*/ *) ; 
 scalar_t__ jsstr_is_heap (int /*<<< orphan*/ *) ; 
 scalar_t__ jsstr_is_inline (int /*<<< orphan*/ *) ; 
 int jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline unsigned jsstr_flush(jsstr_t *str, WCHAR *buf)
{
    unsigned len = jsstr_length(str);
    if(jsstr_is_inline(str)) {
        memcpy(buf, jsstr_as_inline(str)->buf, len*sizeof(WCHAR));
    }else if(jsstr_is_heap(str)) {
        memcpy(buf, jsstr_as_heap(str)->buf, len*sizeof(WCHAR));
    }else {
        jsstr_rope_t *rope = jsstr_as_rope(str);
        jsstr_flush(rope->left, buf);
        jsstr_flush(rope->right, buf+jsstr_length(rope->left));
    }
    return len;
}