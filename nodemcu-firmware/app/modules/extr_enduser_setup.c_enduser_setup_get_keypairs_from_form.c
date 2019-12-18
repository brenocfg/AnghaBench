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
struct keypairs_t {void** keypairs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 int count_char_occurence (char*,char) ; 
 struct keypairs_t* enduser_setup_alloc_keypairs (int) ; 
 int /*<<< orphan*/  enduser_setup_free_keypairs (struct keypairs_t*) ; 
 int enduser_setup_http_urldecode (void*,char*,size_t,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  os_bzero (char*,int) ; 
 int /*<<< orphan*/  os_memcpy (char*,char*,int) ; 
 size_t strlen (char*) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static struct keypairs_t *enduser_setup_get_keypairs_from_form(char *form_body, int form_length) {
  int keypair_nb = count_char_occurence(form_body, '&') + 1;
  int equal_nb = count_char_occurence(form_body, '=');
  
  if (keypair_nb == 1 && equal_nb == 0) {
    ENDUSER_SETUP_DEBUG("No keypair in form body");
    return NULL;
  }

  struct keypairs_t *kp = enduser_setup_alloc_keypairs(keypair_nb);

  int current_idx = 0;
  int err;

  char *body_copy = malloc(form_length+1);
  os_bzero(body_copy, form_length+1);
  os_memcpy(body_copy, form_body, form_length);
  char *tok = strtok(body_copy, "=");
  
  char last_tok = '=';
  while (tok) {
    size_t len = strlen(tok);
    kp->keypairs[current_idx] = malloc(len + 1);
    err = enduser_setup_http_urldecode(kp->keypairs[current_idx], tok, len, len + 1);
    if (err) {
      ENDUSER_SETUP_DEBUG("Unable to decode parameter");
      enduser_setup_free_keypairs(kp);
      free(body_copy);
      return NULL;
    }

    current_idx++;
    if (current_idx > keypair_nb*2) {
      ENDUSER_SETUP_DEBUG("Too many keypairs!");
      enduser_setup_free_keypairs(kp);
      free(body_copy);
      return NULL;
    }

    if (last_tok == '=') {
      tok = strtok(NULL, "&"); // now search for the '&'
      last_tok='&';
    } else {
      tok = strtok(NULL, "="); // search for the next '='
      last_tok='=';
    }
  }
  free(body_copy);
  return kp;
}