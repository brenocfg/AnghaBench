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
 char* MG_DEFAULT_NAMESERVER ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 

__attribute__((used)) static int mg_get_ip_address_of_nameserver(char *name, size_t name_len) {
  int ret = -1;

#ifdef _WIN32
  int i;
  LONG err;
  HKEY hKey, hSub;
  wchar_t subkey[512], value[128],
      *key = L"SYSTEM\\ControlSet001\\Services\\Tcpip\\Parameters\\Interfaces";

  if ((err = RegOpenKeyExW(HKEY_LOCAL_MACHINE, key, 0, KEY_READ, &hKey)) !=
      ERROR_SUCCESS) {
    fprintf(stderr, "cannot open reg key %S: %ld\n", key, err);
    ret = -1;
  } else {
    for (ret = -1, i = 0; 1; i++) {
      DWORD subkey_size = sizeof(subkey), type, len = sizeof(value);
      if (RegEnumKeyExW(hKey, i, subkey, &subkey_size, NULL, NULL, NULL,
                        NULL) != ERROR_SUCCESS) {
        break;
      }
      if (RegOpenKeyExW(hKey, subkey, 0, KEY_READ, &hSub) == ERROR_SUCCESS &&
          ((RegQueryValueExW(hSub, L"NameServer", 0, &type, (void *) value,
                             &len) == ERROR_SUCCESS &&
            value[0] != '\0') ||
           (RegQueryValueExW(hSub, L"DhcpNameServer", 0, &type, (void *) value,
                             &len) == ERROR_SUCCESS &&
            value[0] != '\0'))) {
        /*
         * See https://github.com/cesanta/mongoose/issues/176
         * The value taken from the registry can be empty, a single
         * IP address, or multiple IP addresses separated by comma.
         * If it's empty, check the next interface.
         * If it's multiple IP addresses, take the first one.
         */
        wchar_t *comma = wcschr(value, ',');
        if (comma != NULL) {
          *comma = '\0';
        }
        /* %S will convert wchar_t -> char */
        snprintf(name, name_len, "%S", value);
        ret = 0;
        RegCloseKey(hSub);
        break;
      }
    }
    RegCloseKey(hKey);
  }
#elif MG_ENABLE_FILESYSTEM && defined(MG_RESOLV_CONF_FILE_NAME)
  FILE *fp;
  char line[512];

  if ((fp = mg_fopen(MG_RESOLV_CONF_FILE_NAME, "r")) == NULL) {
    ret = -1;
  } else {
    /* Try to figure out what nameserver to use */
    for (ret = -1; fgets(line, sizeof(line), fp) != NULL;) {
      unsigned int a, b, c, d;
      if (sscanf(line, "nameserver %u.%u.%u.%u", &a, &b, &c, &d) == 4) {
        snprintf(name, name_len, "%u.%u.%u.%u", a, b, c, d);
        ret = 0;
        break;
      }
    }
    (void) fclose(fp);
  }
#else
  snprintf(name, name_len, "%s", MG_DEFAULT_NAMESERVER);
#endif /* _WIN32 */

  return ret;
}