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
struct Patterns {char* pattern; size_t id; scalar_t__ pattern_length; } ;
struct BannerOutput {int dummy; } ;

/* Variables and functions */
 size_t HTTPFIELD_INCOMPLETE ; 
 size_t HTTPFIELD_NEWLINE ; 
 size_t HTTPFIELD_UNKNOWN ; 
 int /*<<< orphan*/  PROTO_HTTP ; 
 int /*<<< orphan*/  banout_append (struct BannerOutput*,int /*<<< orphan*/ ,unsigned char const*,scalar_t__) ; 
 int /*<<< orphan*/  banout_newline (struct BannerOutput*,int /*<<< orphan*/ ) ; 

void
field_name(struct BannerOutput *banout, size_t id,
           struct Patterns *xhttp_fields)
{
    unsigned i;
    if (id == HTTPFIELD_INCOMPLETE)
        return;
    if (id == HTTPFIELD_UNKNOWN)
        return;
    if (id == HTTPFIELD_NEWLINE)
        return;
    for (i=0; xhttp_fields[i].pattern; i++) {
        if (xhttp_fields[i].id == id) {
            banout_newline(banout, PROTO_HTTP);
            banout_append(  banout, PROTO_HTTP,
                            (const unsigned char*)xhttp_fields[i].pattern
                                + ((xhttp_fields[i].pattern[0]=='<')?1:0), /* bah. hack. ugly. */
                            xhttp_fields[i].pattern_length
                                - ((xhttp_fields[i].pattern[0]=='<')?1:0) /* bah. hack. ugly. */
                          );
            return;
        }
    }
}