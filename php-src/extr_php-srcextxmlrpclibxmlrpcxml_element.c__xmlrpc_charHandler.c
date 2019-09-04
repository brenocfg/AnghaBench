#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* current; TYPE_2__* input_options; scalar_t__ needs_enc_conversion; } ;
typedef  TYPE_3__ xml_elem_data ;
struct TYPE_5__ {scalar_t__ encoding; } ;
struct TYPE_4__ {int /*<<< orphan*/  text; } ;

/* Variables and functions */
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  simplestring_addn (int /*<<< orphan*/ *,char const*,int) ; 
 char* utf8_decode (char const*,int,int*,scalar_t__) ; 

__attribute__((used)) static void _xmlrpc_charHandler(void *userData,
                        const char *s,
                        int len)
{
   xml_elem_data* mydata = (xml_elem_data*)userData;
   if(mydata && mydata->current) {

      /* Check if we need to decode utf-8 parser output to another encoding */
      if(mydata->needs_enc_conversion && mydata->input_options->encoding) {
         int new_len = 0;
         char* add_text = utf8_decode(s, len, &new_len, mydata->input_options->encoding);
         if(add_text) {
            len = new_len;
            simplestring_addn(&mydata->current->text, add_text, len);
            efree(add_text);
            return;
         }
      }
      simplestring_addn(&mydata->current->text, s, len);
   }
}