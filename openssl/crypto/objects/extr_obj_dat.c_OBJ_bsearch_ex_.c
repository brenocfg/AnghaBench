const void *OBJ_bsearch_ex_(const void *key, const void *base, int num,
                            int size,
                            int (*cmp) (const void *, const void *),
                            int flags)
{
    const char *p = ossl_bsearch(key, base, num, size, cmp, flags);

#ifdef CHARSET_EBCDIC
    /*
     * THIS IS A KLUDGE - Because the *_obj is sorted in ASCII order, and I
     * don't have perl (yet), we revert to a *LINEAR* search when the object
     * wasn't found in the binary search.
     */
    if (p == NULL) {
        const char *base_ = base;
        int l, h, i = 0, c = 0;

        for (i = 0; i < num; ++i) {
            p = &(base_[i * size]);
            c = (*cmp) (key, p);
            if (c == 0
                || (c < 0 && (flags & OBJ_BSEARCH_VALUE_ON_NOMATCH)))
                return p;
        }
    }
#endif
    return p;
}