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
typedef  int /*<<< orphan*/  uint64_t ;
struct TemplatePacket {int dummy; } ;
struct TCP_ConnectionTable {unsigned int timeout_connection; int timeout_hello; unsigned int count; unsigned int mask; struct Output* out; int /*<<< orphan*/  report_banner; int /*<<< orphan*/  banner1; int /*<<< orphan*/ * packet_buffers; int /*<<< orphan*/ * transmit_queue; struct TemplatePacket* pkt_template; int /*<<< orphan*/  timeouts; int /*<<< orphan*/ * entries; int /*<<< orphan*/  entropy; } ;
struct Output {int dummy; } ;
typedef  int /*<<< orphan*/  PACKET_QUEUE ;
typedef  int /*<<< orphan*/  OUTPUT_REPORT_BANNER ;

/* Variables and functions */
 struct TCP_ConnectionTable* CALLOC (int,int) ; 
 int /*<<< orphan*/  TICKS_FROM_SECS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  banner1_create () ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timeouts_create (int /*<<< orphan*/ ) ; 

struct TCP_ConnectionTable *
tcpcon_create_table(    size_t entry_count,
                        PACKET_QUEUE *transmit_queue,
                        PACKET_QUEUE *packet_buffers,
                        struct TemplatePacket *pkt_template,
                        OUTPUT_REPORT_BANNER report_banner,
                        struct Output *out,
                        unsigned connection_timeout,
                        uint64_t entropy
                        )
{
    struct TCP_ConnectionTable *tcpcon;
    //printf("\nsizeof(TCB) = %u\n\n", (unsigned)sizeof(struct TCP_Control_Block));
    
    
    tcpcon = CALLOC(1, sizeof(*tcpcon));
    tcpcon->timeout_connection = connection_timeout;
    if (tcpcon->timeout_connection == 0)
        tcpcon->timeout_connection = 30; /* half a minute before destroying tcb */
    tcpcon->timeout_hello = 2;
    tcpcon->entropy = entropy;

    /* Find nearest power of 2 to the tcb count, but don't go
     * over the number 16-million */
    {
        size_t new_entry_count;
        new_entry_count = 1;
        while (new_entry_count < entry_count) {
            new_entry_count *= 2;
            if (new_entry_count == 0) {
                new_entry_count = (1<<24);
                break;
            }
        }
        if (new_entry_count > (1<<24))
            new_entry_count = (1<<24);
        if (new_entry_count < (1<<10))
            new_entry_count = (1<<10);
        entry_count = new_entry_count;
    }

    /* Create the table. If we can't allocate enough memory, then shrink
     * the desired size of the table */
    while (tcpcon->entries == 0) {
        tcpcon->entries = malloc(entry_count * sizeof(*tcpcon->entries));
        if (tcpcon->entries == NULL) {
            entry_count >>= 1;
        }
    }
    memset(tcpcon->entries, 0, entry_count * sizeof(*tcpcon->entries));


    /* fill in the table structure */
    tcpcon->count = (unsigned)entry_count;
    tcpcon->mask = (unsigned)(entry_count-1);

    /* create an event/timeouts structure */
    tcpcon->timeouts = timeouts_create(TICKS_FROM_SECS(time(0)));


    tcpcon->pkt_template = pkt_template;

    tcpcon->transmit_queue = transmit_queue;
    tcpcon->packet_buffers = packet_buffers;


    tcpcon->banner1 = banner1_create();

    tcpcon->report_banner = report_banner;
    tcpcon->out = out;
    return tcpcon;
}