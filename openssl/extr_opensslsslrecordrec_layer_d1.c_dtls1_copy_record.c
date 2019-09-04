#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ data; } ;
typedef  TYPE_2__ pitem ;
struct TYPE_10__ {int /*<<< orphan*/ * packet; int /*<<< orphan*/  rrec; int /*<<< orphan*/  rbuf; int /*<<< orphan*/  packet_length; } ;
struct TYPE_7__ {int /*<<< orphan*/ * read_sequence; int /*<<< orphan*/  rrec; int /*<<< orphan*/  rbuf; int /*<<< orphan*/  packet_length; int /*<<< orphan*/ * packet; } ;
struct TYPE_9__ {TYPE_1__ rlayer; } ;
typedef  int /*<<< orphan*/  SSL3_RECORD ;
typedef  int /*<<< orphan*/  SSL3_BUFFER ;
typedef  TYPE_3__ SSL ;
typedef  TYPE_4__ DTLS1_RECORD_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  SSL3_BUFFER_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dtls1_copy_record(SSL *s, pitem *item)
{
    DTLS1_RECORD_DATA *rdata;

    rdata = (DTLS1_RECORD_DATA *)item->data;

    SSL3_BUFFER_release(&s->rlayer.rbuf);

    s->rlayer.packet = rdata->packet;
    s->rlayer.packet_length = rdata->packet_length;
    memcpy(&s->rlayer.rbuf, &(rdata->rbuf), sizeof(SSL3_BUFFER));
    memcpy(&s->rlayer.rrec, &(rdata->rrec), sizeof(SSL3_RECORD));

    /* Set proper sequence number for mac calculation */
    memcpy(&(s->rlayer.read_sequence[2]), &(rdata->packet[5]), 6);

    return 1;
}