#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_8__ {int /*<<< orphan*/  alloc_hint; } ;
struct TYPE_7__ {int frag_len; } ;
struct TYPE_9__ {TYPE_2__ response; TYPE_1__ common; } ;
typedef  TYPE_3__ RpcPktHdr ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PKT_RESPONSE ; 
 int /*<<< orphan*/  RPCRT4_BuildCommonHeader (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

RpcPktHdr *RPCRT4_BuildResponseHeader(ULONG DataRepresentation, ULONG BufferLength)
{
  RpcPktHdr *header;

  header = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(header->response));
  if (header == NULL) {
    return NULL;
  }

  RPCRT4_BuildCommonHeader(header, PKT_RESPONSE, DataRepresentation);
  header->common.frag_len = sizeof(header->response);
  header->response.alloc_hint = BufferLength;

  return header;
}