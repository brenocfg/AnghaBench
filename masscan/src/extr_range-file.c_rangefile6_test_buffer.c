#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct RangeParser {int dummy; } ;
struct TYPE_4__ {int member_0; int member_1; int hi; int lo; } ;
typedef  TYPE_1__ ipv6address ;

/* Variables and functions */
 struct RangeParser* rangeparse_create () ; 
 int /*<<< orphan*/  rangeparse_destroy (struct RangeParser*) ; 
 int /*<<< orphan*/  rangeparse_getipv6 (struct RangeParser*,TYPE_1__*,TYPE_1__*) ; 
 int rangeparse_next (struct RangeParser*,unsigned char const*,size_t*,size_t,unsigned int*,unsigned int*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int
rangefile6_test_buffer(const char *buf,
                       uint64_t in_begin_hi,
                       uint64_t in_begin_lo,
                       uint64_t in_end_hi,
                       uint64_t in_end_lo)
{
    size_t length = strlen(buf);
    size_t offset = 0;
    struct RangeParser *p;
    ipv6address out_begin = {1,2};
    ipv6address out_end = {1,2};
    unsigned tmp1, tmp2;
    int x;
    bool is_found = false;
    
    /* test the entire buffer */
    p = rangeparse_create();
    x = rangeparse_next(p, (const unsigned char *)buf, &offset, length, &tmp1, &tmp2);
    if (x != 2)
        return 1; /*fail*/
    rangeparse_getipv6(p, &out_begin, &out_end);
    if (out_begin.hi != in_begin_hi || out_begin.lo != in_begin_lo)
        return 1; /*fail*/
    if (out_end.hi != in_end_hi || out_end.lo != in_end_lo)
        return 1; /*fail*/
    rangeparse_destroy(p);
    
    /* test one byte at a time */
    p = rangeparse_create();
    offset = 0;
    out_begin.hi = 1;
    out_begin.lo = 2;
    out_end.hi = 1;
    out_end.lo = 2;
    is_found = false;
    while (offset < length) {
        x = rangeparse_next(p, (const unsigned char *)buf, &offset, length, &tmp1, &tmp2);
        if (x == 0)
            continue;
        if (x != 2)
            return 1; /*fail*/
        is_found = true;
        rangeparse_getipv6(p, &out_begin, &out_end);
        if (out_begin.hi != in_begin_hi || out_begin.lo != in_begin_lo)
            return 1; /*fail*/
        if (out_end.hi != in_end_hi || out_end.lo != in_end_lo)
            return 1; /*fail*/
    }
    rangeparse_destroy(p);
    if (!is_found)
        return 1; /*fail*/
    
    return 0;
}