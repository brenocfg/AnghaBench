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
struct buffer {scalar_t__ offset; scalar_t__ len; scalar_t__ capacity; } ;

/* Variables and functions */
 scalar_t__ buf_size_valid (int) ; 
 scalar_t__ buf_valid (struct buffer const*) ; 

__attribute__((used)) static inline bool
buf_safe(const struct buffer *buf, int len)
{
    return buf_valid(buf) && buf_size_valid(len)
           && buf->offset + buf->len + len <= buf->capacity;
}