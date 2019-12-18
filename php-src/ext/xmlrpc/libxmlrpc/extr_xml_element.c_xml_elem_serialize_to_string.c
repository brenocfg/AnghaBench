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
typedef  int /*<<< orphan*/  xml_element ;
struct TYPE_3__ {int len; char* str; } ;
typedef  TYPE_1__ simplestring ;
typedef  int /*<<< orphan*/  XML_ELEM_OUTPUT_OPTIONS ;

/* Variables and functions */
 int /*<<< orphan*/  simplestring_init (TYPE_1__*) ; 
 int /*<<< orphan*/  simplestring_out_fptr ; 
 int /*<<< orphan*/  xml_element_serialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char* xml_elem_serialize_to_string(xml_element *el, XML_ELEM_OUTPUT_OPTIONS options, int *buf_len)
{
   simplestring buf;
   simplestring_init(&buf);

   xml_element_serialize(el, simplestring_out_fptr, (void *)&buf, options, 0);

   if(buf_len) {
      *buf_len = buf.len;
   }

   return buf.str;
}