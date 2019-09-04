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
struct mpv_global {int dummy; } ;
typedef  int /*<<< orphan*/  stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_WRITE ; 
 int /*<<< orphan*/ * stream_create (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mpv_global*) ; 

stream_t *open_output_stream(const char *filename, struct mpv_global *global)
{
    return stream_create(filename, STREAM_WRITE, NULL, global);
}