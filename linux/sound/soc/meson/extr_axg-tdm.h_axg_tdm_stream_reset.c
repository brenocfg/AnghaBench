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
struct axg_tdm_stream {int dummy; } ;

/* Variables and functions */
 int axg_tdm_stream_start (struct axg_tdm_stream*) ; 
 int /*<<< orphan*/  axg_tdm_stream_stop (struct axg_tdm_stream*) ; 

__attribute__((used)) static inline int axg_tdm_stream_reset(struct axg_tdm_stream *ts)
{
	axg_tdm_stream_stop(ts);
	return axg_tdm_stream_start(ts);
}