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
struct TYPE_5__ {int /*<<< orphan*/  cs; } ;
typedef  TYPE_1__ lclContext ;
typedef  int /*<<< orphan*/  TocEntry ;
struct TYPE_6__ {int /*<<< orphan*/  compression; scalar_t__ formatData; } ;
typedef  scalar_t__ Oid ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  AllocateCompressor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteInt (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  _CustomWriteFunc ; 
 int /*<<< orphan*/  fatal (char*) ; 

__attribute__((used)) static void
_StartBlob(ArchiveHandle *AH, TocEntry *te, Oid oid)
{
	lclContext *ctx = (lclContext *) AH->formatData;

	if (oid == 0)
		fatal("invalid OID for large object");

	WriteInt(AH, oid);

	ctx->cs = AllocateCompressor(AH->compression, _CustomWriteFunc);
}