#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  nodetype; scalar_t__ attr; } ;
typedef  TYPE_1__ xmlreader ;
typedef  int /*<<< orphan*/  XmlNodeType ;

/* Variables and functions */
 int /*<<< orphan*/  XmlNodeType_Attribute ; 

__attribute__((used)) static XmlNodeType reader_get_nodetype(const xmlreader *reader)
{
    /* When we're on attribute always return attribute type, container node type is kept.
       Note that container is not necessarily an element, and attribute doesn't mean it's
       an attribute in XML spec terms. */
    return reader->attr ? XmlNodeType_Attribute : reader->nodetype;
}