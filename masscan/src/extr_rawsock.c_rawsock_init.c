void
rawsock_init(void)
{
#ifdef WIN32
    /* Declare and initialize variables */

// It is possible for an adapter to have multiple
// IPv4 addresses, gateways, and secondary WINS servers
// assigned to the adapter.
//
// Note that this sample code only prints out the
// first entry for the IP address/mask, and gateway, and
// the primary and secondary WINS server for each adapter.

    PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter = NULL;
    DWORD dwRetVal = 0;
    UINT i;

/* variables used to print DHCP time info */
    //struct tm newtime;
    //char buffer[32];
    //errno_t error;

    ULONG ulOutBufLen = sizeof (IP_ADAPTER_INFO);
    pAdapterInfo = (IP_ADAPTER_INFO *) malloc(sizeof (IP_ADAPTER_INFO));
    if (pAdapterInfo == NULL) {
        printf("Error allocating memory needed to call GetAdaptersinfo\n");
        return;
    }
// Make an initial call to GetAdaptersInfo to get
// the necessary size into the ulOutBufLen variable
    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *) malloc(ulOutBufLen);
        if (pAdapterInfo == NULL) {
            printf("Error allocating memory needed to call GetAdaptersinfo\n");
            return;
        }
    }

    if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) {
        for (pAdapter = pAdapterInfo; pAdapter; pAdapter = pAdapter->Next) {
            if (pAdapter->Type != MIB_IF_TYPE_ETHERNET)
                continue;

            //printf("\tComboIndex: \t%d\n", pAdapter->ComboIndex);
            //printf("\tAdapter Name: \t%s\n", pAdapter->AdapterName);
            {
                size_t name_len = strlen(pAdapter->AdapterName) + 12 + 1;
                char *name = (char*)malloc(name_len);
                size_t addr_len = pAdapter->AddressLength * 3 + 1;
                char *addr = (char*)malloc(addr_len);

                if (name == NULL || addr == NULL)
                    exit(1);

                sprintf_s(name, name_len, "\\Device\\NPF_%s", pAdapter->AdapterName);

                //printf("\tAdapter Desc: \t%s\n", pAdapter->Description);
                //printf("\tAdapter Addr: \t");
                for (i = 0; i < pAdapter->AddressLength; i++) {
                    if (i == (pAdapter->AddressLength - 1))
                        sprintf_s(addr+i*3, addr_len-i*3, "%.2X", pAdapter->Address[i]);
                    else
                        sprintf_s(addr+i*3, addr_len-i*3, "%.2X-", pAdapter->Address[i]);
                }
                //printf("%s  ->  %s\n", addr, name);
                adapter_names[adapter_name_count].easy_name = addr;
                adapter_names[adapter_name_count].hard_name = name;
                adapter_name_count++;
            }

            //printf("\tIndex: \t%d\n", pAdapter->Index);

            {
                size_t name_len = strlen(pAdapter->AdapterName) + 12 + 1;
                char *name = (char*)malloc(name_len);
                size_t addr_len = strlen(pAdapter->IpAddressList.IpAddress.String) + 1;
                char *addr = (char*)malloc(addr_len);
                if (name == NULL || addr == NULL)
                    exit(1);
                sprintf_s(name, name_len, "\\Device\\NPF_%s", pAdapter->AdapterName);
                sprintf_s(addr, addr_len, "%s", pAdapter->IpAddressList.IpAddress.String);
                //printf("%s  ->  %s\n", addr, name);
                adapter_names[adapter_name_count].easy_name = addr;
                adapter_names[adapter_name_count].hard_name = name;
                adapter_name_count++;
            }

        }
    } else {
        printf("GetAdaptersInfo failed with error: %u\n", 
                                                    (unsigned)dwRetVal);

    }
    if (pAdapterInfo)
        free(pAdapterInfo);
#else
    PFRING_init();
#endif
    return;
}