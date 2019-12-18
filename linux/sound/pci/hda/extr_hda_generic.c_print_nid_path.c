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
struct nid_path {int depth; int /*<<< orphan*/ * path; } ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,char const*,int,char*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_nid_path(struct hda_codec *codec,
			   const char *pfx, struct nid_path *path)
{
	char buf[40];
	char *pos = buf;
	int i;

	*pos = 0;
	for (i = 0; i < path->depth; i++)
		pos += scnprintf(pos, sizeof(buf) - (pos - buf), "%s%02x",
				 pos != buf ? ":" : "",
				 path->path[i]);

	codec_dbg(codec, "%s path: depth=%d '%s'\n", pfx, path->depth, buf);
}