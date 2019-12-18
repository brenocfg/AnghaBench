#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ jsstr_rope_t ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int TMP_BUF_SIZE ; 
 unsigned int jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_rope_extract (TYPE_1__*,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 

__attribute__((used)) static int ropes_cmp(jsstr_rope_t *left, jsstr_rope_t *right)
{
    WCHAR left_buf[TMP_BUF_SIZE], right_buf[TMP_BUF_SIZE];
    unsigned left_len = jsstr_length(&left->str);
    unsigned right_len = jsstr_length(&right->str);
    unsigned cmp_off = 0, cmp_size;
    int ret;

    /* FIXME: We can avoid temporary buffers here. */
    while(cmp_off < min(left_len, right_len)) {
        cmp_size = min(left_len, right_len) - cmp_off;
        if(cmp_size > TMP_BUF_SIZE)
            cmp_size = TMP_BUF_SIZE;

        jsstr_rope_extract(left, cmp_off, cmp_size, left_buf);
        jsstr_rope_extract(right, cmp_off, cmp_size, right_buf);
        ret = memcmp(left_buf, right_buf, cmp_size);
        if(ret)
            return ret;

        cmp_off += cmp_size;
    }

    return left_len - right_len;
}