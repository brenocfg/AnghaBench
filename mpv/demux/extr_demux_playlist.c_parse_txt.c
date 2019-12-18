#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pl_parser {scalar_t__ probing; int /*<<< orphan*/  force; } ;
struct TYPE_4__ {scalar_t__ len; } ;
typedef  TYPE_1__ bstr ;

/* Variables and functions */
 int /*<<< orphan*/  MP_WARN (struct pl_parser*,char*) ; 
 TYPE_1__ bstr_strip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl_add (struct pl_parser*,TYPE_1__) ; 
 int /*<<< orphan*/  pl_eof (struct pl_parser*) ; 
 int /*<<< orphan*/  pl_get_line (struct pl_parser*) ; 

__attribute__((used)) static int parse_txt(struct pl_parser *p)
{
    if (!p->force)
        return -1;
    if (p->probing)
        return 0;
    MP_WARN(p, "Reading plaintext playlist.\n");
    while (!pl_eof(p)) {
        bstr line = bstr_strip(pl_get_line(p));
        if (line.len == 0)
            continue;
        pl_add(p, line);
    }
    return 0;
}