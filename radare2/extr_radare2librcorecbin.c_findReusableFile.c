#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char const* uri; int perm; int /*<<< orphan*/ * desc; } ;
struct TYPE_5__ {int /*<<< orphan*/  files; } ;
typedef  int /*<<< orphan*/  RIODesc ;
typedef  TYPE_1__ RIO ;
typedef  TYPE_2__ FindFile ;

/* Variables and functions */
 int /*<<< orphan*/  findFile ; 
 int /*<<< orphan*/  r_id_storage_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static RIODesc *findReusableFile(RIO *io, const char *uri, int perm) {
	FindFile arg = {
		.uri = uri,
		.perm = perm,
		.desc = NULL,
	};
	r_id_storage_foreach (io->files, findFile, &arg);
	return arg.desc;
}