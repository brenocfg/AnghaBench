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
typedef  int /*<<< orphan*/  uint8_t ;
struct gc_arena {int dummy; } ;
struct buffer {int dummy; } ;
typedef  int /*<<< orphan*/  rnd_bytes ;

/* Variables and functions */
 char const* BSTR (struct buffer*) ; 
 struct buffer alloc_buf_gc (scalar_t__,struct gc_arena*) ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,char const*,char const*) ; 
 char* format_hex_ex (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct gc_arena*) ; 
 int n_rnd_bytes ; 
 int /*<<< orphan*/  prng_bytes (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strlen (char const*) ; 

const char *
hostname_randomize(const char *hostname, struct gc_arena *gc)
{
#define n_rnd_bytes 6

    uint8_t rnd_bytes[n_rnd_bytes];
    const char *rnd_str;
    struct buffer hname = alloc_buf_gc(strlen(hostname)+sizeof(rnd_bytes)*2+4, gc);

    prng_bytes(rnd_bytes, sizeof(rnd_bytes));
    rnd_str = format_hex_ex(rnd_bytes, sizeof(rnd_bytes), 40, 0, NULL, gc);
    buf_printf(&hname, "%s.%s", rnd_str, hostname);
    return BSTR(&hname);
#undef n_rnd_bytes
}