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
struct keypairs_t {int keypairs_nb; char** keypairs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 int /*<<< orphan*/  enduser_setup_free_keypairs (struct keypairs_t*) ; 
 struct keypairs_t* enduser_setup_get_keypairs_from_form (char*,int) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  vfs_close (int) ; 
 int vfs_open (char*,char*) ; 
 int /*<<< orphan*/  vfs_write (int,char*,int) ; 

__attribute__((used)) static int enduser_setup_write_file_with_extra_configuration_data(char *form_body, int form_length) {
  ENDUSER_SETUP_DEBUG("enduser: write data from posted form");
  ENDUSER_SETUP_DEBUG(form_body);

  // We will save the form data into a file in the LUA format: KEY="VALUE", so that configuration data is available for load in the lua code.
  // As input, we have a string as such: "key1=value1&key2=value2&key3=value%203" (urlencoded), the number of '&' tells us how many keypairs there are (the count + 1)
 
  struct keypairs_t *kp = enduser_setup_get_keypairs_from_form(form_body, form_length);
  if (kp == NULL || kp->keypairs_nb == 0) {
    ENDUSER_SETUP_DEBUG("enduser: No extra configuration.");
    if (kp != NULL) enduser_setup_free_keypairs(kp);
    return 1;
  }

  // Now that we have the keys and the values, let's save them in a lua file
  int p_file = vfs_open("eus_params.lua", "w");
  if (p_file == 0)
  {
    ENDUSER_SETUP_DEBUG("Can't open file in write mode!");
    enduser_setup_free_keypairs(kp);
    return 1;
  }

  // write all key pairs as KEY="VALUE"\n into a Lua table, example:
  // local p = {}
  // p.wifi_ssid="ssid"
  // p.wifi_password="password"
  // p.device_name="foo-node"
  // return p
  vfs_write(p_file, "local p={}\n", 11);
  int idx = 0;
  for( idx = 0; idx < kp->keypairs_nb*2; idx=idx+2){
    char* to_write = kp->keypairs[idx];
    size_t length = strlen(to_write);
    
    vfs_write(p_file, "p.", 2);

    vfs_write(p_file, to_write, length);

    vfs_write(p_file, "=\"", 2);
    
    to_write = kp->keypairs[idx+1];
    length = strlen(to_write);
    vfs_write(p_file, to_write, length);

    vfs_write(p_file, "\"\n", 2);
  }
  vfs_write(p_file, "return p\n", 9);

  vfs_close(p_file);
  enduser_setup_free_keypairs(kp);
  // TODO: we could call back in the LUA with an associative table setup, but this is MVP2...
  return 0;
}