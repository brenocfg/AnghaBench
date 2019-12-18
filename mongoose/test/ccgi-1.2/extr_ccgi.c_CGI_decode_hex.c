void *
CGI_decode_hex(const char *p, int *len) {
    unsigned char *out;
    int i, k, n, L, R;

    if (p == 0 || ((n = strlen(p)) & 1)) {
        return 0;  /* length of input must be even */
    }
    out = mymalloc(n / 2 + 1);
    for (i = k = 0; i < n; i += 2) {
        if ((L = hex(p[i])) >= 0 && (R = hex(p[i + 1])) >= 0) {
            out[k++] = (L << 4) + R;
        }
        else {
            free(out);
            return 0;
        }
    }
    out[k] = 0;
    if (len != 0) {
        *len = k;
    }
    return out;
}