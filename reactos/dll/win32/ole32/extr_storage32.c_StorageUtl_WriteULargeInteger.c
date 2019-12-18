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
typedef  int ULONG ;
struct TYPE_5__ {void* LowPart; void* HighPart; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
typedef  TYPE_2__ const ULARGE_INTEGER ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 void* htole32 (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__ const*,int) ; 

void StorageUtl_WriteULargeInteger(BYTE* buffer, ULONG offset,
 const ULARGE_INTEGER *value)
{
#ifdef WORDS_BIGENDIAN
    ULARGE_INTEGER tmp;

    tmp.u.LowPart = htole32(value->u.HighPart);
    tmp.u.HighPart = htole32(value->u.LowPart);
    memcpy(buffer + offset, &tmp, sizeof(ULARGE_INTEGER));
#else
    memcpy(buffer + offset, value, sizeof(ULARGE_INTEGER));
#endif
}