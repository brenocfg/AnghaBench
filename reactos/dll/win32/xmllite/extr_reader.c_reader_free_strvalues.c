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

/* Variables and functions */
 int StringValue_Last ; 
 int /*<<< orphan*/  reader_free_strvalue (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void reader_free_strvalues(xmlreader *reader)
{
    int type;
    for (type = 0; type < StringValue_Last; type++)
        reader_free_strvalue(reader, type);
}