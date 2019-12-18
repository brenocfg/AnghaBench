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
struct gc_arena {int dummy; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 struct buffer alloc_buf_gc (scalar_t__,struct gc_arena*) ; 
 int /*<<< orphan*/  buf_write (struct buffer*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  check_expected (char const*) ; 
 scalar_t__ mock () ; 
 scalar_t__ strlen (char const*) ; 

struct buffer
__wrap_buffer_read_from_file(const char *filename, struct gc_arena *gc)
{
    check_expected(filename);

    const char *pem_str = (const char *) mock();
    struct buffer ret = alloc_buf_gc(strlen(pem_str) + 1, gc);
    buf_write(&ret, pem_str, strlen(pem_str) + 1);

    return ret;
}