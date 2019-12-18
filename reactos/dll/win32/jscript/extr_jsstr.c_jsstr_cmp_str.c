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
struct TYPE_5__ {int /*<<< orphan*/ * right; int /*<<< orphan*/ * left; } ;
typedef  TYPE_1__ jsstr_rope_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {int /*<<< orphan*/  buf; } ;
struct TYPE_6__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
#define  JSSTR_HEAP 130 
#define  JSSTR_INLINE 129 
#define  JSSTR_ROPE 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_4__* jsstr_as_heap (int /*<<< orphan*/ *) ; 
 TYPE_3__* jsstr_as_inline (int /*<<< orphan*/ *) ; 
 TYPE_1__* jsstr_as_rope (int /*<<< orphan*/ *) ; 
 unsigned int jsstr_length (int /*<<< orphan*/ *) ; 
 int jsstr_tag (int /*<<< orphan*/ *) ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 

__attribute__((used)) static int jsstr_cmp_str(jsstr_t *jsstr, const WCHAR *str, unsigned len)
{
    int ret;

    switch(jsstr_tag(jsstr)) {
    case JSSTR_INLINE:
        ret = memcmp(jsstr_as_inline(jsstr)->buf, str, len*sizeof(WCHAR));
        return ret || jsstr_length(jsstr) == len ? ret : 1;
    case JSSTR_HEAP:
        ret = memcmp(jsstr_as_heap(jsstr)->buf, str, len*sizeof(WCHAR));
        return ret || jsstr_length(jsstr) == len ? ret : 1;
    case JSSTR_ROPE: {
        jsstr_rope_t *rope = jsstr_as_rope(jsstr);
        unsigned left_len = jsstr_length(rope->left);

        ret = jsstr_cmp_str(rope->left, str, min(len, left_len));
        if(ret || len <= left_len)
            return ret;
        return jsstr_cmp_str(rope->right, str+left_len, len-left_len);
    }
    }

    assert(0);
    return 0;
}