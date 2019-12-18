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
struct bitstream {int current; int* buffer; int /*<<< orphan*/  length; } ;
typedef  int DWORD ;
typedef  int BYTE ;

/* Variables and functions */

__attribute__((used)) static const char *lookup_code(const BYTE *table, DWORD table_size, struct bitstream *bits)
{
    const BYTE *p = table;

    while (p < table + table_size && *p == 0x80)
    {
        if (p + 2 >= table + table_size) return NULL;

        if (!(bits->current & 0xff))
        {
            if (!bits->length) return NULL;
            bits->current = (*bits->buffer << 8) | 1;
            bits->buffer++;
            bits->length--;
        }

        if (bits->current & 0x8000)
        {
            p += 3;
        }
        else
        {
            p = table + (*(p + 2) | (*(p + 1) << 8));
        }

        bits->current <<= 1;
    }

    if (p + 1 < table + table_size && *(p + 1))
    {
        /* FIXME: Whats the meaning of *p? */
        const BYTE *q = p + 1;
        while (q < table + table_size && *q) q++;
        return (q < table + table_size) ? (const char *)(p + 1) : NULL;
    }

    return NULL;
}