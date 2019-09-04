#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  storage_number ;
typedef  int calculated_number ;
struct TYPE_11__ {TYPE_2__* dimensions; int /*<<< orphan*/  update_every; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct TYPE_10__ {char* name; char* id; struct TYPE_10__* next; int /*<<< orphan*/ * values; } ;
struct TYPE_9__ {long d; int* od; int* v; int* o; TYPE_3__* st; scalar_t__ after; scalar_t__ before; int /*<<< orphan*/  update_every; } ;
typedef  int RRDR_VALUE_FLAGS ;
typedef  int RRDR_OPTIONS ;
typedef  TYPE_1__ RRDR ;
typedef  TYPE_2__ RRDDIM ;
typedef  int /*<<< orphan*/  BUFFER ;

/* Variables and functions */
 int RRDR_DIMENSION_HIDDEN ; 
 int RRDR_DIMENSION_NONZERO ; 
 int RRDR_OPTION_ABSOLUTE ; 
 int RRDR_OPTION_GOOGLE_JSON ; 
 int RRDR_OPTION_NONZERO ; 
 int RRDR_OPTION_NULL2ZERO ; 
 int RRDR_OPTION_PERCENTAGE ; 
 int RRDR_VALUE_EMPTY ; 
 int /*<<< orphan*/  buffer_rrd_value (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  buffer_sprintf (int /*<<< orphan*/ *,char*,char*,char*,...) ; 
 int /*<<< orphan*/  buffer_strcat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  does_storage_number_exist (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rrdr_buffer_print_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rrdr_rows (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdset_check_rdlock (TYPE_3__*) ; 
 scalar_t__ rrdset_first_entry_t (TYPE_3__*) ; 
 scalar_t__ rrdset_last_entry_t (TYPE_3__*) ; 
 size_t rrdset_last_slot (TYPE_3__*) ; 
 scalar_t__ unlikely (int) ; 
 int unpack_storage_number (int /*<<< orphan*/ ) ; 

void rrdr_json_wrapper_begin(RRDR *r, BUFFER *wb, uint32_t format, RRDR_OPTIONS options, int string_value) {
    rrdset_check_rdlock(r->st);

    long rows = rrdr_rows(r);
    long c, i;
    RRDDIM *rd;

    //info("JSONWRAPPER(): %s: BEGIN", r->st->id);
    char kq[2] = "",                    // key quote
            sq[2] = "";                     // string quote

    if( options & RRDR_OPTION_GOOGLE_JSON ) {
        kq[0] = '\0';
        sq[0] = '\'';
    }
    else {
        kq[0] = '"';
        sq[0] = '"';
    }

    buffer_sprintf(wb, "{\n"
                       "   %sapi%s: 1,\n"
                       "   %sid%s: %s%s%s,\n"
                       "   %sname%s: %s%s%s,\n"
                       "   %sview_update_every%s: %d,\n"
                       "   %supdate_every%s: %d,\n"
                       "   %sfirst_entry%s: %u,\n"
                       "   %slast_entry%s: %u,\n"
                       "   %sbefore%s: %u,\n"
                       "   %safter%s: %u,\n"
                       "   %sdimension_names%s: ["
                   , kq, kq
                   , kq, kq, sq, r->st->id, sq
                   , kq, kq, sq, r->st->name, sq
                   , kq, kq, r->update_every
                   , kq, kq, r->st->update_every
                   , kq, kq, (uint32_t)rrdset_first_entry_t(r->st)
                   , kq, kq, (uint32_t)rrdset_last_entry_t(r->st)
                   , kq, kq, (uint32_t)r->before
                   , kq, kq, (uint32_t)r->after
                   , kq, kq);

    for(c = 0, i = 0, rd = r->st->dimensions; rd && c < r->d ;c++, rd = rd->next) {
        if(unlikely(r->od[c] & RRDR_DIMENSION_HIDDEN)) continue;
        if(unlikely((options & RRDR_OPTION_NONZERO) && !(r->od[c] & RRDR_DIMENSION_NONZERO))) continue;

        if(i) buffer_strcat(wb, ", ");
        buffer_strcat(wb, sq);
        buffer_strcat(wb, rd->name);
        buffer_strcat(wb, sq);
        i++;
    }
    if(!i) {
#ifdef NETDATA_INTERNAL_CHECKS
        error("RRDR is empty for %s (RRDR has %d dimensions, options is 0x%08x)", r->st->id, r->d, options);
#endif
        rows = 0;
        buffer_strcat(wb, sq);
        buffer_strcat(wb, "no data");
        buffer_strcat(wb, sq);
    }

    buffer_sprintf(wb, "],\n"
                       "   %sdimension_ids%s: ["
                   , kq, kq);

    for(c = 0, i = 0, rd = r->st->dimensions; rd && c < r->d ;c++, rd = rd->next) {
        if(unlikely(r->od[c] & RRDR_DIMENSION_HIDDEN)) continue;
        if(unlikely((options & RRDR_OPTION_NONZERO) && !(r->od[c] & RRDR_DIMENSION_NONZERO))) continue;

        if(i) buffer_strcat(wb, ", ");
        buffer_strcat(wb, sq);
        buffer_strcat(wb, rd->id);
        buffer_strcat(wb, sq);
        i++;
    }
    if(!i) {
        rows = 0;
        buffer_strcat(wb, sq);
        buffer_strcat(wb, "no data");
        buffer_strcat(wb, sq);
    }

    buffer_sprintf(wb, "],\n"
                       "   %slatest_values%s: ["
                   , kq, kq);

    for(c = 0, i = 0, rd = r->st->dimensions; rd && c < r->d ;c++, rd = rd->next) {
        if(unlikely(r->od[c] & RRDR_DIMENSION_HIDDEN)) continue;
        if(unlikely((options & RRDR_OPTION_NONZERO) && !(r->od[c] & RRDR_DIMENSION_NONZERO))) continue;

        if(i) buffer_strcat(wb, ", ");
        i++;

        storage_number n = rd->values[rrdset_last_slot(r->st)];

        if(!does_storage_number_exist(n))
            buffer_strcat(wb, "null");
        else
            buffer_rrd_value(wb, unpack_storage_number(n));
    }
    if(!i) {
        rows = 0;
        buffer_strcat(wb, "null");
    }

    buffer_sprintf(wb, "],\n"
                       "   %sview_latest_values%s: ["
                   , kq, kq);

    i = 0;
    if(rows) {
        calculated_number total = 1;

        if(unlikely(options & RRDR_OPTION_PERCENTAGE)) {
            total = 0;
            for(c = 0, rd = r->st->dimensions; rd && c < r->d ;c++, rd = rd->next) {
                calculated_number *cn = &r->v[ (rrdr_rows(r) - 1) * r->d ];
                calculated_number n = cn[c];

                if(likely((options & RRDR_OPTION_ABSOLUTE) && n < 0))
                    n = -n;

                total += n;
            }
            // prevent a division by zero
            if(total == 0) total = 1;
        }

        for(c = 0, i = 0, rd = r->st->dimensions; rd && c < r->d ;c++, rd = rd->next) {
            if(unlikely(r->od[c] & RRDR_DIMENSION_HIDDEN)) continue;
            if(unlikely((options & RRDR_OPTION_NONZERO) && !(r->od[c] & RRDR_DIMENSION_NONZERO))) continue;

            if(i) buffer_strcat(wb, ", ");
            i++;

            calculated_number *cn = &r->v[ (rrdr_rows(r) - 1) * r->d ];
            RRDR_VALUE_FLAGS *co = &r->o[ (rrdr_rows(r) - 1) * r->d ];
            calculated_number n = cn[c];

            if(co[c] & RRDR_VALUE_EMPTY) {
                if(options & RRDR_OPTION_NULL2ZERO)
                    buffer_strcat(wb, "0");
                else
                    buffer_strcat(wb, "null");
            }
            else {
                if(unlikely((options & RRDR_OPTION_ABSOLUTE) && n < 0))
                    n = -n;

                if(unlikely(options & RRDR_OPTION_PERCENTAGE))
                    n = n * 100 / total;

                buffer_rrd_value(wb, n);
            }
        }
    }
    if(!i) {
        rows = 0;
        buffer_strcat(wb, "null");
    }

    buffer_sprintf(wb, "],\n"
                       "   %sdimensions%s: %ld,\n"
                       "   %spoints%s: %ld,\n"
                       "   %sformat%s: %s"
                   , kq, kq, i
                   , kq, kq, rows
                   , kq, kq, sq
    );

    rrdr_buffer_print_format(wb, format);

    buffer_sprintf(wb, "%s,\n"
                       "   %sresult%s: "
                   , sq
                   , kq, kq
    );

    if(string_value) buffer_strcat(wb, sq);
    //info("JSONWRAPPER(): %s: END", r->st->id);
}