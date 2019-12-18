#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int readOnly; int /*<<< orphan*/ * name; int /*<<< orphan*/ * fileset; int /*<<< orphan*/ * files; } ;
typedef  int /*<<< orphan*/  File ;
typedef  TYPE_1__ BufFile ;

/* Variables and functions */
 TYPE_1__* makeBufFileCommon (int) ; 
 scalar_t__ palloc (int) ; 

__attribute__((used)) static BufFile *
makeBufFile(File firstfile)
{
	BufFile    *file = makeBufFileCommon(1);

	file->files = (File *) palloc(sizeof(File));
	file->files[0] = firstfile;
	file->readOnly = false;
	file->fileset = NULL;
	file->name = NULL;

	return file;
}