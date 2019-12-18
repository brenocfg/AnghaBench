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
struct TYPE_3__ {int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
typedef  TYPE_1__ jsstr_rope_t ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  jsstr_extract (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 unsigned int jsstr_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jsstr_rope_extract(jsstr_rope_t *str, unsigned off, unsigned len, WCHAR *buf)
{
    unsigned left_len = jsstr_length(str->left);

    if(left_len <= off) {
        jsstr_extract(str->right, off-left_len, len, buf);
    }else if(left_len >= len+off) {
        jsstr_extract(str->left, off, len, buf);
    }else {
        left_len -= off;
        jsstr_extract(str->left, off, left_len, buf);
        jsstr_extract(str->right, 0, len-left_len, buf+left_len);
    }
}