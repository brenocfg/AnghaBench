#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ time_t ;
struct timeout {scalar_t__ when; struct timeout* next; int /*<<< orphan*/  what; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;} ;
struct protocol {int /*<<< orphan*/  (* handler ) (struct protocol*) ;struct interface_info* local; struct protocol* next; } ;
struct interface_info {int /*<<< orphan*/  dead; } ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/ * AdapterStateChangedEvent ; 
 int /*<<< orphan*/  ApiLock () ; 
 int /*<<< orphan*/  ApiUnlock () ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  DH_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ DhcpSocket ; 
 int /*<<< orphan*/  FALSE ; 
 int FD_CLOSE ; 
 int FD_READ ; 
 int INFINITE ; 
 int INT_MAX ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int NO_ERROR ; 
 scalar_t__ StartAdapterDiscovery () ; 
 int WAIT_OBJECT_0 ; 
 int /*<<< orphan*/  WSACloseEvent (scalar_t__) ; 
 scalar_t__ WSACreateEvent () ; 
 int WSAEventSelect (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  WSAResetEvent (scalar_t__) ; 
 scalar_t__ WSA_INVALID_EVENT ; 
 int WaitForMultipleObjects (int,scalar_t__*,int /*<<< orphan*/ ,int) ; 
 struct timeout* free_timeouts ; 
 int /*<<< orphan*/  got_one (struct protocol*) ; 
 struct protocol* protocols ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct protocol*) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 
 struct timeout* timeouts ; 

void
dispatch(HANDLE hStopEvent)
{
    int count, to_msec;
    struct protocol *l;
    time_t howlong, cur_time;
    HANDLE Events[3];
    int EventCount = 2;

    Events[0] = StartAdapterDiscovery();
    if (!Events[0])
         return;

    AdapterStateChangedEvent = Events[0];

    Events[1] = hStopEvent;
    Events[2] = WSA_INVALID_EVENT;

    ApiLock();

    do {
        /*
         * Call any expired timeouts, and then if there's still
         * a timeout registered, time out the select call then.
         */
        time(&cur_time);

        if (timeouts)
        {
            struct timeout *t;

            if (timeouts->when <= cur_time) {
                t = timeouts;
                timeouts = timeouts->next;
                (*(t->func))(t->what);
                t->next = free_timeouts;
                free_timeouts = t;
                continue;
            }

            /*
             * Figure timeout in milliseconds, and check for
             * potential overflow, so we can cram into an
             * int for poll, while not polling with a
             * negative timeout and blocking indefinitely.
             */
            howlong = timeouts->when - cur_time;
            if (howlong > INT_MAX / 1000)
                howlong = INT_MAX / 1000;
            to_msec = howlong * 1000;
        }
        else
        {
            to_msec = INFINITE;
        }

        if (Events[2] == WSA_INVALID_EVENT && DhcpSocket != INVALID_SOCKET)
        {
            Events[2] = WSACreateEvent();
            if (Events[2] != WSA_INVALID_EVENT)
            {
                count = WSAEventSelect(DhcpSocket, Events[2], FD_READ | FD_CLOSE);
                if (count != NO_ERROR)
                {
                    WSACloseEvent(Events[2]);
                    Events[2] = WSA_INVALID_EVENT;
                }
                else
                {
                    EventCount = 3;
                }
            }
        }
        else if (Events[2] != WSA_INVALID_EVENT && DhcpSocket == INVALID_SOCKET)
        {
            WSACloseEvent(Events[2]);
            Events[2] = WSA_INVALID_EVENT;

            EventCount = 2;
        }

        ApiUnlock();
        count = WaitForMultipleObjects(EventCount,
                                       Events,
                                       FALSE,
                                       to_msec);
        ApiLock();
        if (count == WAIT_OBJECT_0)
        {
            /* Adapter state change */
            continue;
        }
        else if (count == WAIT_OBJECT_0 + 1)
        {
            /* Stop event signalled */
            break;
        }
        else if (count == WAIT_OBJECT_0 + 2)
        {
            /* Packet received */

            /* WSA events are manual reset events */
            WSAResetEvent(Events[2]);
        }
        else
        {
            /* Timeout */
            continue;
        }

        for (l = protocols; l; l = l->next) {
            struct interface_info *ip;
            ip = l->local;
            if (ip && (l->handler != got_one ||
                        !ip->dead)) {
                DH_DbgPrint(MID_TRACE,("Handling %x\n", l));
                (*(l->handler))(l);
            }
        }
    } while (1);

    AdapterStateChangedEvent = NULL;
    CloseHandle(Events[0]);
    CloseHandle(Events[1]);
    WSACloseEvent(Events[2]);

    ApiUnlock();
}