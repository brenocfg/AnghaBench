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
typedef  int /*<<< orphan*/  xml_element ;
typedef  int /*<<< orphan*/  XML_ELEM_OUTPUT_OPTIONS ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  file_out_fptr ; 
 int /*<<< orphan*/  xml_element_serialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void xml_elem_serialize_to_stream(xml_element *el, FILE *output, XML_ELEM_OUTPUT_OPTIONS options)
{
   xml_element_serialize(el, file_out_fptr, (void *)output, options, 0);
}