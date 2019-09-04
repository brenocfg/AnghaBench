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
struct ffmpeg_muxer {int /*<<< orphan*/  pipe; } ;
struct dstr {int /*<<< orphan*/  array; } ;

/* Variables and functions */
 int /*<<< orphan*/  build_command_line (struct ffmpeg_muxer*,struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  os_process_pipe_create (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline void start_pipe(struct ffmpeg_muxer *stream, const char *path)
{
	struct dstr cmd;
	build_command_line(stream, &cmd, path);
	stream->pipe = os_process_pipe_create(cmd.array, "w");
	dstr_free(&cmd);
}