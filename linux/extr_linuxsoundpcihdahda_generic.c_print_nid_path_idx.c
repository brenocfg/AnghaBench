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
struct nid_path {int dummy; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_nid_path (struct hda_codec*,char const*,struct nid_path*) ; 
 struct nid_path* snd_hda_get_path_from_idx (struct hda_codec*,int) ; 

__attribute__((used)) static inline void print_nid_path_idx(struct hda_codec *codec,
				      const char *pfx, int idx)
{
	struct nid_path *path;

	path = snd_hda_get_path_from_idx(codec, idx);
	if (path)
		print_nid_path(codec, pfx, path);
}