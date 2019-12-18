#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* time_t ;
struct TYPE_14__ {scalar_t__ period; int offset; scalar_t__ last; void* next; void* directory; int /*<<< orphan*/  filesize; } ;
struct TYPE_10__ {void* stylesheet; } ;
struct TYPE_8__ {int /*<<< orphan*/  ip; int /*<<< orphan*/  port; } ;
struct Output {int is_virgin_file; int format; TYPE_7__ rotate; int /*<<< orphan*/ * fp; int /*<<< orphan*/ * funcs; int /*<<< orphan*/ * src; void* filename; TYPE_3__ xml; int /*<<< orphan*/  is_append; int /*<<< orphan*/  is_show_host; int /*<<< orphan*/  is_show_closed; int /*<<< orphan*/  is_show_open; int /*<<< orphan*/  is_interactive; int /*<<< orphan*/  is_gmt; int /*<<< orphan*/  is_banner; TYPE_1__ redis; void* when_scan_started; struct Masscan const* masscan; } ;
struct TYPE_12__ {scalar_t__ timeout; int offset; scalar_t__* directory; int /*<<< orphan*/  filesize; } ;
struct TYPE_13__ {int format; TYPE_5__ rotate; scalar_t__* filename; scalar_t__* stylesheet; int /*<<< orphan*/  is_append; int /*<<< orphan*/  is_show_host; int /*<<< orphan*/  is_show_closed; int /*<<< orphan*/  is_show_open; int /*<<< orphan*/  is_interactive; } ;
struct TYPE_9__ {int /*<<< orphan*/  ip; int /*<<< orphan*/  port; } ;
struct Masscan {int nic_count; TYPE_6__ output; TYPE_4__* nic; int /*<<< orphan*/  is_gmt; int /*<<< orphan*/  is_banners; TYPE_2__ redis; } ;
struct TYPE_11__ {int /*<<< orphan*/  src; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct Output* CALLOC (int,int) ; 
 scalar_t__ LONG_MAX ; 
#define  Output_Binary 137 
#define  Output_Certs 136 
#define  Output_Grepable 135 
#define  Output_JSON 134 
#define  Output_List 133 
#define  Output_NDJSON 132 
#define  Output_None 131 
#define  Output_Redis 130 
#define  Output_Unicornscan 129 
#define  Output_XML 128 
 int /*<<< orphan*/  binary_output ; 
 int /*<<< orphan*/  certs_output ; 
 void* duplicate_string (scalar_t__*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  grepable_output ; 
 void* indexed_filename (scalar_t__*,unsigned int) ; 
 int /*<<< orphan*/  json_output ; 
 int /*<<< orphan*/  ndjson_output ; 
 void* next_rotate_time (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  null_output ; 
 int /*<<< orphan*/ * open_rotate (struct Output*,scalar_t__*) ; 
 int /*<<< orphan*/  perror (scalar_t__*) ; 
 int /*<<< orphan*/  redis_output ; 
 int /*<<< orphan*/  text_output ; 
 void* time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unicornscan_output ; 
 int /*<<< orphan*/  xml_output ; 

struct Output *
output_create(const struct Masscan *masscan, unsigned thread_index)
{
    struct Output *out;
    unsigned i;

    /* allocate/initialize memory */
    out = CALLOC(1, sizeof(*out));
    out->masscan = masscan;
    out->when_scan_started = time(0);
    out->is_virgin_file = 1;

    /*
     * Copy the configuration information from the 'masscan' structure.
     */
    out->rotate.period = masscan->output.rotate.timeout;
    out->rotate.offset = masscan->output.rotate.offset;
    out->rotate.filesize = masscan->output.rotate.filesize;
    out->redis.port = masscan->redis.port;
    out->redis.ip = masscan->redis.ip;
    out->is_banner = masscan->is_banners;
    out->is_gmt = masscan->is_gmt;
    out->is_interactive = masscan->output.is_interactive;
    out->is_show_open = masscan->output.is_show_open;
    out->is_show_closed = masscan->output.is_show_closed;
    out->is_show_host = masscan->output.is_show_host;
    out->is_append = masscan->output.is_append;
    out->xml.stylesheet = duplicate_string(masscan->output.stylesheet);
    out->rotate.directory = duplicate_string(masscan->output.rotate.directory);
    if (masscan->nic_count <= 1)
        out->filename = duplicate_string(masscan->output.filename);
    else
        out->filename = indexed_filename(masscan->output.filename, thread_index);

    for (i=0; i<8; i++) {
        out->src[i] = masscan->nic[i].src;
    }

    /*
     * Link the appropriate output module.
     * TODO: support multiple output modules
     */
    out->format = masscan->output.format;
    switch (out->format) {
    case Output_List:
        out->funcs = &text_output;
        break;
    case Output_Unicornscan:
        out->funcs = &unicornscan_output;
        break;
    case Output_XML:
        out->funcs = &xml_output;
        break;
    case Output_JSON:
        out->funcs = &json_output;
        break;
    case Output_NDJSON:
        out->funcs = &ndjson_output;
        break;
    case Output_Certs:
        out->funcs = &certs_output;
        break;
    case Output_Binary:
        out->funcs = &binary_output;
        break;
    case Output_Grepable:
        out->funcs = &grepable_output;
        break;
    case Output_Redis:
        out->funcs = &redis_output;
        break;
    case Output_None:
        out->funcs = &null_output;
        break;
    default:
        out->funcs = &null_output;
        break;
    }

    /*
     * Open the desired output file. We do this now at the start of the scan
     * so that we can immediately notify the user of an error, rather than
     * waiting midway through a long scan and have it fail.
     */
    if (masscan->output.filename[0] && out->funcs != &null_output) {
        FILE *fp;

        fp = open_rotate(out, masscan->output.filename);
        if (fp == NULL) {
            perror(masscan->output.filename);
            exit(1);
        }

        out->fp = fp;
        out->rotate.last = time(0);
    }

    /*
     * Set the time of the next rotation. If we aren't rotating files, then
     * this time will be set at "infinity" in the future.
     * TODO: this code isn't Y2036 compliant.
     */
    if (masscan->output.rotate.timeout == 0) {
        /* TODO: how does one find the max time_t value??*/
        out->rotate.next = (time_t)LONG_MAX;
    } else {
        if (out->rotate.offset > 1) {
            out->rotate.next = next_rotate_time(
                                    out->rotate.last-out->rotate.period,
                                    out->rotate.period, out->rotate.offset);
        } else {
            out->rotate.next = next_rotate_time(
                                    out->rotate.last,
                                    out->rotate.period, out->rotate.offset);
        }
    }



    return out;
}