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
typedef  char const* uint8_t ;
struct gc_arena {int dummy; } ;
struct buffer {scalar_t__ data; } ;

/* Variables and functions */
 unsigned int FHE_CAPS ; 
 unsigned int FHE_SPACE_BREAK_MASK ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ SIZE_MAX ; 
 struct buffer alloc_buf_gc (size_t const,struct gc_arena*) ; 
 int /*<<< orphan*/  buf_catrunc (struct buffer*,char*) ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,char const* const) ; 
 int /*<<< orphan*/  static_assert (int,char*) ; 
 size_t strlen (char const*) ; 

char *
format_hex_ex(const uint8_t *data, int size, int maxoutput,
              unsigned int space_break_flags, const char *separator,
              struct gc_arena *gc)
{
    const size_t bytes_per_hexblock = space_break_flags & FHE_SPACE_BREAK_MASK;
    const size_t separator_len = separator ? strlen(separator) : 0;
    static_assert(INT_MAX <= SIZE_MAX, "Code assumes INT_MAX <= SIZE_MAX");
    const size_t out_len = maxoutput > 0 ? maxoutput :
                           ((size * 2) + ((size / bytes_per_hexblock) * separator_len) + 2);

    struct buffer out = alloc_buf_gc(out_len, gc);
    for (int i = 0; i < size; ++i)
    {
        if (separator && i && !(i % bytes_per_hexblock))
        {
            buf_printf(&out, "%s", separator);
        }
        if (space_break_flags & FHE_CAPS)
        {
            buf_printf(&out, "%02X", data[i]);
        }
        else
        {
            buf_printf(&out, "%02x", data[i]);
        }
    }
    buf_catrunc(&out, "[more...]");
    return (char *)out.data;
}