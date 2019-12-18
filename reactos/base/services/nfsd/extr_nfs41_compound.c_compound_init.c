#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  nfs_resop4 ;
typedef  int /*<<< orphan*/  nfs_argop4 ;
typedef  int /*<<< orphan*/  nfs41_compound_res ;
struct TYPE_7__ {int /*<<< orphan*/ * resarray; scalar_t__ resarray_count; int /*<<< orphan*/  tag_len; } ;
struct TYPE_5__ {int minorversion; int /*<<< orphan*/ * argarray; scalar_t__ argarray_count; scalar_t__ tag_len; int /*<<< orphan*/  tag; } ;
struct TYPE_6__ {TYPE_4__ res; TYPE_1__ args; } ;
typedef  TYPE_2__ nfs41_compound ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_OPAQUE_LIMIT ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_4__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

void compound_init(
    nfs41_compound *compound,
    nfs_argop4 *argops,
    nfs_resop4 *resops,
    const char *tag)
{
    /* initialize args */
    compound->args.tag_len = (uint32_t)strlen(tag);
    memcpy(compound->args.tag, tag, compound->args.tag_len);
    compound->args.minorversion = 1;
    compound->args.argarray_count = 0;
    compound->args.argarray = argops;

    /* initialize results */
    ZeroMemory(&compound->res, sizeof(nfs41_compound_res));
    compound->res.tag_len = NFS4_OPAQUE_LIMIT;
    compound->res.resarray_count = 0;
    compound->res.resarray = resops;
}