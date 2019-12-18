#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int timeline; TYPE_1__* walmethod; } ;
struct TYPE_4__ {int (* existsfile ) (char*) ;} ;
typedef  TYPE_2__ StreamCtl ;

/* Variables and functions */
 int MAXFNAMELEN ; 
 int /*<<< orphan*/  TLHistoryFileName (char*,int) ; 
 int stub1 (char*) ; 

__attribute__((used)) static bool
existsTimeLineHistoryFile(StreamCtl *stream)
{
	char		histfname[MAXFNAMELEN];

	/*
	 * Timeline 1 never has a history file. We treat that as if it existed,
	 * since we never need to stream it.
	 */
	if (stream->timeline == 1)
		return true;

	TLHistoryFileName(histfname, stream->timeline);

	return stream->walmethod->existsfile(histfname);
}