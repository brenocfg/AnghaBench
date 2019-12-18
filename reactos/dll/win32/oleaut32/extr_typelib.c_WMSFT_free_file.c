#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_15__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  data; } ;
struct TYPE_20__ {int /*<<< orphan*/  data; } ;
struct TYPE_19__ {int /*<<< orphan*/  data; } ;
struct TYPE_18__ {int /*<<< orphan*/  data; } ;
struct TYPE_17__ {int /*<<< orphan*/  data; } ;
struct TYPE_31__ {int /*<<< orphan*/  data; } ;
struct TYPE_30__ {int /*<<< orphan*/  data; } ;
struct TYPE_29__ {int /*<<< orphan*/  data; } ;
struct TYPE_28__ {int /*<<< orphan*/  data; } ;
struct TYPE_27__ {int /*<<< orphan*/  data; } ;
struct TYPE_26__ {int /*<<< orphan*/  data; } ;
struct TYPE_25__ {int /*<<< orphan*/  data; } ;
struct TYPE_24__ {int /*<<< orphan*/  data; } ;
struct TYPE_23__ {int /*<<< orphan*/  data; } ;
struct TYPE_22__ {TYPE_14__ aux_seg; TYPE_13__ cdguids_seg; TYPE_12__ custdata_seg; TYPE_11__ arraydesc_seg; TYPE_10__ typdesc_seg; TYPE_9__ string_seg; TYPE_8__ name_seg; TYPE_7__ namehash_seg; TYPE_6__ impfile_seg; TYPE_5__ impinfo_seg; TYPE_4__ ref_seg; TYPE_3__ guid_seg; TYPE_2__ guidhash_seg; TYPE_1__ typeinfo_seg; } ;
typedef  TYPE_15__ WMSFT_TLBFile ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void WMSFT_free_file(WMSFT_TLBFile *file)
{
    HeapFree(GetProcessHeap(), 0, file->typeinfo_seg.data);
    HeapFree(GetProcessHeap(), 0, file->guidhash_seg.data);
    HeapFree(GetProcessHeap(), 0, file->guid_seg.data);
    HeapFree(GetProcessHeap(), 0, file->ref_seg.data);
    HeapFree(GetProcessHeap(), 0, file->impinfo_seg.data);
    HeapFree(GetProcessHeap(), 0, file->impfile_seg.data);
    HeapFree(GetProcessHeap(), 0, file->namehash_seg.data);
    HeapFree(GetProcessHeap(), 0, file->name_seg.data);
    HeapFree(GetProcessHeap(), 0, file->string_seg.data);
    HeapFree(GetProcessHeap(), 0, file->typdesc_seg.data);
    HeapFree(GetProcessHeap(), 0, file->arraydesc_seg.data);
    HeapFree(GetProcessHeap(), 0, file->custdata_seg.data);
    HeapFree(GetProcessHeap(), 0, file->cdguids_seg.data);
    HeapFree(GetProcessHeap(), 0, file->aux_seg.data);
}