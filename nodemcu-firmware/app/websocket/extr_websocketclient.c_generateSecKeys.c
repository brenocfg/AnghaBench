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

/* Variables and functions */
 char* WS_GUID ; 
 int WS_GUID_LENGTH ; 
 char* base64Encode (char*,int) ; 
 char* cryptoSha1 (char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_random () ; 

__attribute__((used)) static void generateSecKeys(char **key, char **expectedKey) {
  char rndData[16];
  int i;
  for (i = 0; i < 16; i++) {
    rndData[i] = (char) os_random();
  }

  *key = base64Encode(rndData, 16);

  // expectedKey = b64(sha1(keyB64 + GUID))
  char keyWithGuid[24 + WS_GUID_LENGTH];
  memcpy(keyWithGuid, *key, 24);
  memcpy(keyWithGuid + 24, WS_GUID, WS_GUID_LENGTH);

  char *keyEncrypted = cryptoSha1(keyWithGuid, 24 + WS_GUID_LENGTH);
  *expectedKey = base64Encode(keyEncrypted, 20);

  os_free(keyEncrypted);
}