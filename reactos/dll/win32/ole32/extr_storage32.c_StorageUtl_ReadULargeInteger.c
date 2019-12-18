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
typedef  TYPE_2__ ULARGE_INTEGER ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 void* htole32 (void*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/  const*,int) ; 

void StorageUtl_ReadULargeInteger(const BYTE* buffer, ULONG offset,
 ULARGE_INTEGER* value)
{
#ifdef WORDS_BIGENDIAN
    ULARGE_INTEGER tmp;

    memcpy(&tmp, buffer + offset, sizeof(ULARGE_INTEGER));
    value->u.LowPart = htole32(tmp.u.HighPart);
    value->u.HighPart = htole32(tmp.u.LowPart);
#else
    memcpy(value, buffer + offset, sizeof(ULARGE_INTEGER));
#endif
}