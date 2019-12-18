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
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PING_STRING_SIZE ; 
 int buf_string_match (struct buffer const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ping_string ; 

__attribute__((used)) static inline bool
is_ping_msg(const struct buffer *buf)
{
    return buf_string_match(buf, ping_string, PING_STRING_SIZE);
}