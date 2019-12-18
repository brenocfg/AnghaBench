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
struct snd_soc_dapm_path {int connect; int /*<<< orphan*/  sink; int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int /*<<< orphan*/  dapm_mark_dirty (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dapm_path_invalidate (struct snd_soc_dapm_path*) ; 

__attribute__((used)) static void soc_dapm_connect_path(struct snd_soc_dapm_path *path,
	bool connect, const char *reason)
{
	if (path->connect == connect)
		return;

	path->connect = connect;
	dapm_mark_dirty(path->source, reason);
	dapm_mark_dirty(path->sink, reason);
	dapm_path_invalidate(path);
}