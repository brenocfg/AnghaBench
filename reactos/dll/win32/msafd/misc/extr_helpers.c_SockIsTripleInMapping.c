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
typedef  size_t ULONG ;
struct TYPE_5__ {size_t Rows; TYPE_1__* Mapping; } ;
struct TYPE_4__ {scalar_t__ Protocol; scalar_t__ SocketType; scalar_t__ AddressFamily; } ;
typedef  TYPE_2__* PWINSOCK_MAPPING ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 

BOOL
SockIsTripleInMapping(
    PWINSOCK_MAPPING Mapping,
    INT AddressFamily,
    INT SocketType,
    INT Protocol)
{
    /* The Windows version returns more detailed information on which of the 3 parameters failed...we should do this later */
    ULONG    Row;

    TRACE("Called, Mapping rows = %d\n", Mapping->Rows);

    /* Loop through Mapping to Find a matching one */
    for (Row = 0; Row < Mapping->Rows; Row++) {
        TRACE("Examining: row %d: AF %d type %d proto %d\n",
				Row,
				(INT)Mapping->Mapping[Row].AddressFamily,
				(INT)Mapping->Mapping[Row].SocketType,
				(INT)Mapping->Mapping[Row].Protocol);

        /* Check of all three values Match */
        if (((INT)Mapping->Mapping[Row].AddressFamily == AddressFamily) &&
            ((INT)Mapping->Mapping[Row].SocketType == SocketType) &&
            ((INT)Mapping->Mapping[Row].Protocol == Protocol)) {
            TRACE("Found\n");
            return TRUE;
        }
    }
    WARN("Not found\n");
    return FALSE;
}