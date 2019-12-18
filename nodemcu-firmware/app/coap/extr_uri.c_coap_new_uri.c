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
typedef  int /*<<< orphan*/  coap_uri_t ;

/* Variables and functions */
 char* URI_DATA (unsigned char*) ; 
 scalar_t__ coap_split_uri (char*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ malloc (unsigned int) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned char const*,unsigned int) ; 

coap_uri_t * coap_new_uri(const unsigned char *uri, unsigned int length) {
  unsigned char *result;

  result = (unsigned char *)malloc(length + 1 + sizeof(coap_uri_t));

  if (!result)
    return NULL;

  memcpy(URI_DATA(result), uri, length);
  URI_DATA(result)[length] = '\0'; /* make it zero-terminated */

  if (coap_split_uri(URI_DATA(result), length, (coap_uri_t *)result) < 0) {
    free(result);
    return NULL;
  }
  return (coap_uri_t *)result;
}