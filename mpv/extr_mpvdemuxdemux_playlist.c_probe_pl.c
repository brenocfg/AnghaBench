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
struct pl_parser {int force; int /*<<< orphan*/  s; } ;
struct pl_format {scalar_t__ (* parse ) (struct pl_parser*) ;int /*<<< orphan*/  mime_types; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int MP_ARRAY_SIZE (struct pl_format*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct pl_parser*,char*) ; 
 scalar_t__ check_mimetype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pl_format* formats ; 
 int /*<<< orphan*/  stream_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_tell (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct pl_parser*) ; 

__attribute__((used)) static const struct pl_format *probe_pl(struct pl_parser *p)
{
    int64_t start = stream_tell(p->s);
    for (int n = 0; n < MP_ARRAY_SIZE(formats); n++) {
        const struct pl_format *fmt = &formats[n];
        stream_seek(p->s, start);
        if (check_mimetype(p->s, fmt->mime_types)) {
            MP_VERBOSE(p, "forcing format by mime-type.\n");
            p->force = true;
            return fmt;
        }
        if (fmt->parse(p) >= 0)
            return fmt;
    }
    return NULL;
}