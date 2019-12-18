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
struct pl_parser {int /*<<< orphan*/  pl; } ;
typedef  int /*<<< orphan*/  bstr ;

/* Variables and functions */
 char* bstrto0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  playlist_add_file (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

__attribute__((used)) static void pl_add(struct pl_parser *p, bstr entry)
{
    char *s = bstrto0(NULL, entry);
    playlist_add_file(p->pl, s);
    talloc_free(s);
}