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
typedef  enum demux_check { ____Placeholder_demux_check } demux_check ;

/* Variables and functions */
#define  DEMUX_CHECK_FORCE 131 
#define  DEMUX_CHECK_NORMAL 130 
#define  DEMUX_CHECK_REQUEST 129 
#define  DEMUX_CHECK_UNSAFE 128 
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static const char *d_level(enum demux_check level)
{
    switch (level) {
    case DEMUX_CHECK_FORCE:  return "force";
    case DEMUX_CHECK_UNSAFE: return "unsafe";
    case DEMUX_CHECK_REQUEST:return "request";
    case DEMUX_CHECK_NORMAL: return "normal";
    }
    abort();
}