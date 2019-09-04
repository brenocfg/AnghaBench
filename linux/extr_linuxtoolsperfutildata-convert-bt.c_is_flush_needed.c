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
struct ctf_stream {scalar_t__ count; } ;

/* Variables and functions */
 scalar_t__ STREAM_FLUSH_COUNT ; 

__attribute__((used)) static bool is_flush_needed(struct ctf_stream *cs)
{
	return cs->count >= STREAM_FLUSH_COUNT;
}