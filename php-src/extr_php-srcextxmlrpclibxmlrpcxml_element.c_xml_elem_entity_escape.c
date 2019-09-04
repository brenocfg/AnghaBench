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
typedef  int XML_ELEM_ESCAPING ;

/* Variables and functions */
 scalar_t__ create_xml_escape (char*,unsigned char const) ; 
 char* emalloc (int) ; 
 scalar_t__ entity_length (unsigned char const) ; 
 scalar_t__ markup (unsigned char const) ; 
 scalar_t__ non_ascii (unsigned char const) ; 
 scalar_t__ non_print (unsigned char const) ; 
 int strlen (char const*) ; 
 int xml_elem_markup_escaping ; 
 int xml_elem_non_ascii_escaping ; 
 int xml_elem_non_print_escaping ; 

__attribute__((used)) static char* xml_elem_entity_escape(const char* buf, int old_len, int *newlen, XML_ELEM_ESCAPING flags) {
  char *pRetval = 0;
  int iNewBufLen=0;

#define should_escape(c, flag) ( ((flag & xml_elem_markup_escaping) && markup(c)) || \
                                 ((flag & xml_elem_non_ascii_escaping) && non_ascii(c)) || \
                                 ((flag & xml_elem_non_print_escaping) && non_print(c)) )

  if(buf && *buf) {
    const unsigned char *bufcopy;
    char *NewBuffer;
    int ToBeXmlEscaped=0;
    int iLength;
    bufcopy = (const unsigned char *) buf;
    iLength= old_len ? old_len : strlen(buf);
    while(*bufcopy) {
      if( should_escape(*bufcopy, flags) ) {
	/* the length will increase by length of xml escape - the character length */
	iLength += entity_length(*bufcopy);
	ToBeXmlEscaped=1;
      }
      bufcopy++;
    }

    if(ToBeXmlEscaped) {

      NewBuffer= emalloc(iLength+1);
      if(NewBuffer) {
	bufcopy = (const unsigned char *) buf;
	while(*bufcopy) {
	  if(should_escape(*bufcopy, flags)) {
	    iNewBufLen += create_xml_escape(NewBuffer+iNewBufLen,*bufcopy);
	  }
	  else {
	    NewBuffer[iNewBufLen++]=*bufcopy;
	  }
	  bufcopy++;
	}
	NewBuffer[iNewBufLen] = 0;
	pRetval = NewBuffer;
      }
    }
  }

  if(newlen) {
     *newlen = iNewBufLen;
  }

  return pRetval;
}