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
struct RangeParser {int dummy; } ;

/* Variables and functions */
 struct RangeParser* rangeparse_create () ; 
 int /*<<< orphan*/  rangeparse_destroy (struct RangeParser*) ; 
 int rangeparse_next (struct RangeParser*,unsigned char const*,size_t*,size_t,unsigned int*,unsigned int*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int
rangefile_test_buffer(const char *buf, unsigned in_begin, unsigned in_end)
{
    size_t length = strlen(buf);
    size_t offset = 0;
    struct RangeParser *p;
    unsigned out_begin = 0xa3a3a3a3;
    unsigned out_end  = 0xa3a3a3a3;
    int x;
    bool is_found = false;

    /* test the entire buffer */
    p = rangeparse_create();
    x = rangeparse_next(p, (const unsigned char *)buf, &offset, length, &out_begin, &out_end);
    if (x != 1)
        return 1; /*fail*/
    if (in_begin != out_begin || in_end != out_end)
        return 1; /*fail*/
    rangeparse_destroy(p);

    /* test one byte at a time */
    p = rangeparse_create();
    offset = 0;
    out_begin = 0xa3a3a3a3;
    out_end  = 0xa3a3a3a3;
    is_found = false;
    while (offset < length) {
        x = rangeparse_next(p, (const unsigned char *)buf, &offset, length, &out_begin, &out_end);
        if (x == 0)
            continue;
        if (x < 0)
            return 1; /*fail*/
        is_found = true;    
        if (in_begin != out_begin || in_end != out_end)
            return 1; /*fail*/
    }
    rangeparse_destroy(p);
    if (!is_found)
        return 1; /*fail*/

    return 0;
}