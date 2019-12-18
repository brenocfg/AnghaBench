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
typedef  int /*<<< orphan*/  xmlreader ;
struct element {int /*<<< orphan*/  qname; int /*<<< orphan*/  localname; int /*<<< orphan*/  prefix; } ;

/* Variables and functions */
 int /*<<< orphan*/  reader_free (int /*<<< orphan*/ *,struct element*) ; 
 int /*<<< orphan*/  reader_free_strvalued (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reader_free_element(xmlreader *reader, struct element *element)
{
    reader_free_strvalued(reader, &element->prefix);
    reader_free_strvalued(reader, &element->localname);
    reader_free_strvalued(reader, &element->qname);
    reader_free(reader, element);
}