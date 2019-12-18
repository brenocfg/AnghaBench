#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltKeyTablePtr ;
typedef  int /*<<< orphan*/  xsltKeyTable ;
struct TYPE_5__ {int /*<<< orphan*/ * keys; struct TYPE_5__* nameURI; struct TYPE_5__* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlHashFree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltFreeNodeSetEntry ; 

__attribute__((used)) static void
xsltFreeKeyTable(xsltKeyTablePtr keyt) {
    if (keyt == NULL)
	return;
    if (keyt->name != NULL)
	xmlFree(keyt->name);
    if (keyt->nameURI != NULL)
	xmlFree(keyt->nameURI);
    if (keyt->keys != NULL)
	xmlHashFree(keyt->keys, xsltFreeNodeSetEntry);
    memset(keyt, -1, sizeof(xsltKeyTable));
    xmlFree(keyt);
}